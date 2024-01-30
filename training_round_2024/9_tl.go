package main

//
//import (
//	"bufio"
//	"os"
//	"sort"
//	"strconv"
//	"strings"
//)
//
//type Point struct {
//	x, y int
//}
//
//type Rectangle struct {
//	Min, Max Point
//	Children []*Rectangle
//}
//
//func (r1 *Rectangle) IsOutsideFor(r2 *Rectangle) bool {
//	return r1.Min.x < r2.Min.x && r1.Min.y < r2.Min.y &&
//		r1.Max.x > r2.Max.x && r1.Max.y > r2.Max.y
//}
//
//func isMinCorner(matrix []string, row, col int) bool {
//	if string(matrix[row][col]) == "*" {
//		if row == 0 {
//			if col == 0 {
//				return true
//			} else if string(matrix[row][col-1]) == "." {
//				return true
//			}
//		} else if col == 0 && string(matrix[row-1][col]) == "." {
//			return true
//		} else {
//			return string(matrix[row-1][col]) == "." && string(matrix[row][col-1]) == "."
//		}
//	}
//	return false
//}
//
//func main() {
//	in := bufio.NewReader(os.Stdin)
//	out := bufio.NewWriter(os.Stdout)
//
//	tmp, _ := in.ReadString('\n')
//	testsCount, _ := strconv.Atoi(strings.TrimSpace(tmp))
//
//	for i := 0; i < testsCount; i++ {
//		tmp, _ = in.ReadString('\n')
//		line := strings.Split(strings.TrimSpace(tmp), " ")
//		n, _ := strconv.Atoi(line[0])
//		m, _ := strconv.Atoi(line[1])
//		var matrix []string
//		for j := 0; j < n; j++ {
//			tmp, _ = in.ReadString('\n')
//			matrix = append(matrix, strings.TrimSpace(tmp))
//		}
//		var res []int
//		rectangle := &Rectangle{Point{0, 0}, Point{n - 1, m - 1}, []*Rectangle{}}
//		for row := 0; row < n; row++ {
//			for col := 0; col < m; col++ {
//				if isMinCorner(matrix, row, col) {
//					x, y := row, col
//					for y+1 < m && string(matrix[x][y+1]) != "." {
//						y++
//					}
//					for x+1 < n && string(matrix[x+1][y]) != "." {
//						x++
//					}
//					r := &Rectangle{Point{row, col}, Point{x, y}, []*Rectangle{}}
//					var level int
//					parent := rectangle
//					for {
//						end := true
//						for _, k := range parent.Children {
//							if k.IsOutsideFor(r) {
//								parent = k
//								level++
//								end = false
//								break
//							}
//						}
//						if end {
//							parent.Children = append(parent.Children, r)
//							break
//						}
//					}
//					res = append(res, level)
//					col = y
//				}
//			}
//		}
//		sort.Slice(res, func(i, j int) bool {
//			return res[i] < res[j]
//		})
//		for _, el := range res {
//			out.WriteString(strconv.Itoa(el) + " ")
//		}
//		out.WriteString("\n")
//	}
//	out.Flush()
//}
