package main

import (
	"fmt"
)

func main() {
	s1, s2 := []int{1, 2, 3}, []int{4, 5, 6, 7, 8}
	fmt.Println(zip(s1, s2)) // [[1 4] [2 5] [3 6]]
}

func zip(s1 []int, s2 []int) [][]int {
	pairCount := min(len(s1), len(s2))
	result := make([][]int, pairCount)
	for i := 0; i < pairCount; i++ {
		result[i] = []int{s1[i], s2[i]}
	}
	return result
}
