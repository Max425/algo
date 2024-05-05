package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	One   uint8 = '1'
	Two   uint8 = '2'
	Three uint8 = '3'
	Four  uint8 = '4'
	Five  uint8 = '5'
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	mark := map[byte]int{One: 0, Two: 1, Three: 2, Four: 3, Five: 4}
	var t int
	fmt.Fscanln(in, &t)
	for test := 0; test < t; test++ {
		var n, m int
		fmt.Fscanln(in, &n, &m)
		grades := make([][]byte, n)
		rowCounter := make([][]int, n)
		colCounter := make([][]int, m)
		for i := 0; i < n; i++ {
			grades[i] = make([]byte, m)
			for j := 0; j < m; j++ {
				fmt.Fscanf(in, "%c", &grades[i][j])
				mar := grades[i][j]
				if mar < Five {
					if len(rowCounter[i]) == 0 {
						rowCounter[i] = append(rowCounter[i], 0, 0, 0, 0)
					}
					rowCounter[i][mark[mar]]++

					if len(colCounter[j]) == 0 {
						colCounter[j] = append(colCounter[j], 0, 0, 0, 0)
					}
					colCounter[j][mark[mar]]++
				}
			}
			fmt.Fscanln(in)
		}
		row := searchMin(rowCounter)

		newColCounter := make([][]int, m)
		for i := 0; i < n; i++ {
			if i == row {
				continue
			}
			for j := 0; j < m; j++ {
				mar := grades[i][j]
				if mar >= Five {
					continue
				}
				if len(newColCounter[j]) == 0 {
					newColCounter[j] = append(newColCounter[j], 0, 0, 0, 0)
				}
				newColCounter[j][mark[mar]]++
			}
		}
		col := searchMin(newColCounter)
		///
		///
		///

		col1 := searchMin(colCounter)
		newRowCounter := make([][]int, n)
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {
				if j == col1 {
					continue
				}
				mar := grades[i][j]
				if mar >= Five {
					continue
				}
				if len(newRowCounter[i]) == 0 {
					newRowCounter[i] = append(newRowCounter[i], 0, 0, 0, 0)
				}
				newRowCounter[i][mark[mar]]++
			}
		}
		row1 := searchMin(newRowCounter)

		///
		///
		///
		minMark1, minMark2 := Five, Five
		for i := 0; i < n; i++ {
			for j := 0; j < m; j++ {

				mar := grades[i][j]
				if mar < minMark1 {
					if i != row && j != col {
						minMark1 = mar
					}
				}
				if mar < minMark2 {
					if i != row1 && j != col1 {
						minMark2 = mar
					}
				}
			}
		}
		if minMark1 < minMark2 {
			fmt.Fprintln(out, row1+1, col1+1)
		} else {
			fmt.Fprintln(out, row+1, col+1)
		}

	}
}

func searchMin(counter [][]int) int {
	if len(counter) < 2 {
		return len(counter)
	}

	minIndex := 0
	minArray := counter[0]
	for i := 1; i < len(counter); i++ {
		if isLess(counter[i], minArray) {
			minArray = counter[i]
			minIndex = i
		}
	}
	return minIndex
}

func isLess(arr1, arr2 []int) bool {
	if len(arr1) == 0 || len(arr2) == 0 {
		return len(arr2) == 0
	}
	for i := 0; i < len(arr1); i++ {
		if arr1[i] > arr2[i] {
			return true
		} else if arr1[i] < arr2[i] {
			return false
		}
	}
	return false
}
