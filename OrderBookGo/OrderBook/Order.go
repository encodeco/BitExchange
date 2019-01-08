package OrderBook

import "fmt"

type Order struct{
	price		uint64;
	quantity	uint;
}

func ( o Order ) OrderPrint(){
	fmt.Println("order");
}
