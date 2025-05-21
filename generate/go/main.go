package main

import (
	"fmt"
)

func main() {
	p := int64(19)
	q := int64(23)
	seed := int64(7)
	count := 5

	result := BBSGenerate(count, p, q, seed)

	fmt.Print("BBS sequence: ")
	for _, x := range result {
		fmt.Printf("%d ", x)
	}
	fmt.Println()
}
