import sys
import array as arr
import redis
import json
from pprint import pprint

import time

def main(argv):
    # My code here
    myredis = redis.Redis(host='localhost', port=6379, db=0)

    current_milli_time = lambda: int(round(time.time() * 1000))

    #print millis
    
    o_id = 1 # order id

    with open('../sample_data/testdata2.json') as data_file:    
        data = json.load(data_file)
        for item in data:

            newitem = []

            newitem.append(str(o_id))
            newitem.append(item["type"][0].upper())
            newitem.append(item["side"][0].upper())
            newitem.append(str(item["quantity"]))
            newitem.append(str(item["price"]))
            newitem.append(str(item["trade_id"]))
            newitem.append(str(current_milli_time()))

            insertstring = "-".join(newitem)
            myredis.rpush("order", insertstring)

            o_id = o_id + 1

            print(insertstring)
    
    #pprint(data)
    pass

if __name__ == "__main__":
    main(sys.argv)
