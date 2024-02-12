package main

import (
	"bufio"
	"fmt"
	"os"
)

func LeftCorner(data [][]byte, latter byte, x, y int) {
	if y%2 != 0 {
		y--
		data[x][y] = latter
	}
	for x != 0 {
		x--
		data[x][y] = latter
	}
	for y != 0 {
		y--
		data[x][y] = latter
	}
}

func RightCorner(data [][]byte, latter byte, x, y, n, m int) {
	if y%2 != 0 {
		y++
		data[x][y] = latter
	}
	for x != n-1 {
		x++
		data[x][y] = latter
	}
	for y != m-1 {
		y++
		data[x][y] = latter
	}
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	var convert = map[string]byte{"A": 'a', "B": 'b'}
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		var n, m int
		fmt.Fscanln(in, &n, &m)
		var data [][]byte
		for j := 0; j < n; j++ {
			var line string
			fmt.Fscanln(in, &line)
			data = append(data, []byte(line))
		}
		isFirst := true
		for x := 0; x < n; x++ {
			for y := 0; y < m; y++ {
				point := string(data[x][y])
				if point == "A" || point == "B" {
					if isFirst {
						LeftCorner(data, convert[point], x, y)
						isFirst = false
					} else {
						RightCorner(data, convert[point], x, y, n, m)
					}
				}
			}
		}
		for _, l := range data {
			fmt.Fprintln(out, string(l))
		}
	}
}
