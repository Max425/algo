package main

import (
	"fmt"
	"strconv"
)

// четыре однопалубных корабля,
// три двухпалубных корабля,
// два трёхпалубных корабля,
// один четырёхпалубный корабль.
func main() {
	var n int
	fmt.Scanf("%d\n", &n)
	for i := 0; i < n; i++ {
		counter := make([]int, 4)
		for j := 0; j < 10; j++ {
			var el string
			fmt.Scanf("%s", &el)
			ship, _ := strconv.Atoi(el)
			counter[ship-1]++
		}
		if counter[0] == 4 && counter[1] == 3 && counter[2] == 2 && counter[3] == 1 {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}
}
