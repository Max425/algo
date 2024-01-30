package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var n int
	fmt.Scanf("%d\n", &n)
	for i := 0; i < n; i++ {
		var k int
		fmt.Scanf("%d\n", &k)
		var s string
		res := make([]bool, k+1)
		fmt.Scanf("%s\r\n", &s)
		arr := strings.Split(s, ",")
		for _, el := range arr {
			if strings.Contains(el, "-") {
				prom := strings.Split(el, "-")
				st, _ := strconv.Atoi(prom[0])
				end, _ := strconv.Atoi(prom[1])
				for ; st <= end; st++ {
					res[st] = true
				}
			} else {
				st, _ := strconv.Atoi(el)
				res[st] = true
			}
		}
		var is bool
		for j := 1; j < len(res); j++ {
			if !res[j] {
				if is {
					fmt.Printf(",")
				}
				is = true
				fmt.Printf("%d", j)
				var flag bool
				for j+1 < len(res) && !res[j+1] {
					flag = true
					j++
				}
				if flag {
					fmt.Printf("-%d", j)
				}
			}
		}
		fmt.Printf("\n")
	}
}
