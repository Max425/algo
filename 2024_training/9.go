package main

import (
	"bufio"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Point struct {
	x, y int
}

type Rectangle struct {
	Min, Max Point
	Level    int
}

func isMinCorner(matrix *[]string, row, col int) bool {
	if string((*matrix)[row][col]) == "*" {
		if row == 0 {
			if col == 0 {
				return true
			} else if string((*matrix)[row][col-1]) == "." {
				return true
			}
		} else if col == 0 && string((*matrix)[row-1][col]) == "." {
			return true
		} else {
			return string((*matrix)[row-1][col]) == "." && string((*matrix)[row][col-1]) == "."
		}
	}
	return false
}

func Count(matrix *[]string, result *[]int, parent *Rectangle, isVisited *map[Point]*Rectangle) {
	for row := parent.Min.x; row < parent.Max.x; row++ {
		for col := parent.Min.y; col < parent.Max.y; col++ {
			p := Point{row, col}
			rectangle, ok := (*isVisited)[p]
			if !ok && isMinCorner(matrix, row, col) {
				x, y := row, col
				for y+1 < parent.Max.y && string((*matrix)[x][y+1]) != "." {
					y++
				}
				for x+1 < parent.Max.x && string((*matrix)[x+1][y]) != "." {
					x++
				}
				r := &Rectangle{Point{row + 2, col + 2}, Point{x - 1, y - 1}, parent.Level + 1}

				x1 := row
				for x1+1 < parent.Max.x && string((*matrix)[x1+1][col]) != "." {
					x1++
					point := Point{x1, col}
					(*isVisited)[point] = r
				}

				*result = append(*result, r.Level)
				col = y
				(*isVisited)[p] = r
				Count(matrix, result, r, isVisited)
			}
			if ok {
				col = rectangle.Max.y
			}
		}
	}
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)

	tmp, _ := in.ReadString('\n')
	testsCount, _ := strconv.Atoi(strings.TrimSpace(tmp))

	for i := 0; i < testsCount; i++ {
		tmp, _ = in.ReadString('\n')
		line := strings.Split(strings.TrimSpace(tmp), " ")
		n, _ := strconv.Atoi(line[0])
		m, _ := strconv.Atoi(line[1])
		var matrix []string
		for j := 0; j < n; j++ {
			tmp, _ = in.ReadString('\n')
			matrix = append(matrix, strings.TrimSpace(tmp))
		}
		var result []int
		isVisited := make(map[Point]*Rectangle)
		rectangle := &Rectangle{Point{0, 0}, Point{n, m}, -1}
		Count(&matrix, &result, rectangle, &isVisited)

		// вывод
		sort.Slice(result, func(i, j int) bool {
			return result[i] < result[j]
		})
		for _, el := range result {
			out.WriteString(strconv.Itoa(el) + " ")
		}
		out.WriteString("\n")
	}
	out.Flush()
}
