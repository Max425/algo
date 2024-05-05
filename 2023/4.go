package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

// Электронная таблица
func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		fmt.Fscanln(in)
		var n, m int
		fmt.Fscanf(in, "%d %d\n", &n, &m)
		matrix := readMatrix(in, n, m)
		var k int
		fmt.Fscanln(in, &k)
		line, _ := in.ReadString('\n')
		for _, col := range dirtyStringToSplice(line) {
			sort.SliceStable(matrix, func(i, j int) bool {
				return matrix[i][col-1] < matrix[j][col-1]
			})
		}
		printMatrix(out, matrix, n, m)
	}
}

func printMatrix(out *bufio.Writer, matrix [][]int, n, m int) {
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Fprintf(out, "%d ", matrix[i][j])
		}
		fmt.Fprintln(out)
	}
	fmt.Fprintln(out)
}

func readMatrix(in *bufio.Reader, n, m int) [][]int {
	var matrix [][]int
	for j := 0; j < n; j++ {
		line, _ := in.ReadString('\n')
		matrix = append(matrix, dirtyStringToSplice(line))
	}

	return matrix
}

func dirtyStringToSplice(line string) []int {
	data := strings.Split(strings.TrimSpace(line), " ")
	nums := make([]int, len(data))
	for i, el := range data {
		num, _ := strconv.Atoi(el)
		nums[i] = num
	}

	return nums
}
