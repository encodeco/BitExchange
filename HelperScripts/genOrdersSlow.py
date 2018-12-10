#! /usr/bin/python
from __future__ import print_function
from random import *
import sys
import redis
import time
sys.path.append('..')
#from orderbook import OrderBook

myredis = redis.Redis(host='localhost', port=6379, db=0)

def generate_new_buy(trade_id):
    return {'type' : 'limit', 
           'side' : 'bid', 
           'quantity' : randint(1,1000),
           'price' : randint(900,1050),
           'trade_id' : trade_id}
           
def generate_cross_buy(trade_id):
    return {'type' : 'limit', 
            'side' : 'bid', 
            'quantity' : randint(1,1000), 
            'price' : randint(1055,1200),
            'trade_id' : trade_id}

def generate_new_sell(trade_id):
    return {'type' : 'limit', 
            'side' : 'ask', 
            'quantity' : randint(1,1000), 
            'price' : randint(1055,1200),
            'trade_id' : trade_id}
            
def generate_cross_sell(trade_id):
    return {'type' : 'limit', 
            'side' : 'ask', 
            'quantity' : randint(1,1000),
            'price' : randint(900,1050),
            'trade_id' : trade_id}

def gen_orders(nb_orders_prefilled, verbose = False):
    
    o_id = 0
    orders = []
    for trade_id in range(nb_orders_prefilled):
        orders.append( generate_new_buy(trade_id) )
        orders.append( generate_new_buy(trade_id) )
        orders.append( generate_cross_buy(trade_id) )
        orders.append( generate_new_sell(trade_id) )
        orders.append( generate_new_sell(trade_id) )

        orders.append( generate_new_sell(trade_id) )
        orders.append( generate_new_sell(trade_id) )
        orders.append( generate_cross_sell(trade_id) )
        orders.append( generate_new_sell(trade_id) )
        orders.append( generate_new_sell(trade_id) )
        
    for order in orders:
        newitem = []

        newitem.append(str(o_id))
        newitem.append(order["type"][0].upper())
        newitem.append(order["side"][0].upper())
        newitem.append(str(order["quantity"]))
        newitem.append(str(order["price"]))
        newitem.append(str(order["trade_id"]))
        newitem.append(str(current_milli_time()))

        insertstring = "-".join(newitem)
        myredis.rpush("order", insertstring)

        o_id = o_id + 1
        print (o_id)
        time.sleep(1)
        
def current_milli_time():
   return int(round(time.time() * 1000))

def main(argv):
    
    # nb buys and sells to prefill orderbook
    gen_orders(100)

    #pprint(data)
    pass

if __name__ == "__main__":
    main(sys.argv)


