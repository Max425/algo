package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	var n int
	fmt.Scanf("%d\n", &n)
	reader := bufio.NewReader(os.Stdin)
	for i := 0; i < n; i++ {
		reader.ReadString('\n')
		text, _ := reader.ReadString('\n')

		nums := strings.Split(strings.TrimSpace(text), " ")
		var ints, res []int

		for _, s := range nums {
			num, _ := strconv.Atoi(s)
			ints = append(ints, num)
		}
		var col int
		el := ints[0]
		for j := 0; j < len(ints); j++ {
			if j+1 == len(ints) {
				res = append(res, el, col)
				break
			}
			if ints[j] == ints[j+1]-1 && col >= 0 {
				col++
			} else if ints[j] == ints[j+1]+1 && col <= 0 {
				col--
			} else {
				res = append(res, el, col)
				el = ints[j+1]
				col = 0
			}
		}
		fmt.Println(len(res))
		for _, num := range res {
			fmt.Printf("%d ", num)
		}
	}
}
