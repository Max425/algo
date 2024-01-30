package main

import (
	"fmt"
	"strconv"
)

func main() {
	var n, m int
	fmt.Scanf("%d\n", &n)

	for i := 0; i < n; i++ {
		fmt.Scanf("%d\n", &m)

		l, r := 15, 30
		for j := 0; j < m; j++ {
			var s1, s2 string
			fmt.Scanf("%s %s\n", &s1, &s2)
			num, _ := strconv.Atoi(s2)
			switch s1 {
			case ">=":
				l = max(l, num)
			case "<=":
				r = min(r, num)
			}
			if l <= r {
				fmt.Println(l)
			} else {
				fmt.Println(-1)
			}
		}
		fmt.Println()
	}
}
