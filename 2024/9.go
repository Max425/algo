package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	X  = "X"
	Y  = "Y"
	Z  = "Z"
	XY = "XY"
	XZ = "XZ"
	YZ = "YZ"
)

func CheckPair(commands string) bool {
	counter := make(map[string]int, 6)
	for _, command := range commands {
		switch command {
		case 'X':
			counter[X]++
		case 'Y':
			if counter[X] > 0 {
				counter[X]--
				counter[XY]++
			} else {
				counter[Y]++
			}
		case 'Z':
			if counter[X] > 0 {
				counter[X]--
				counter[XZ]++
			} else if counter[Y] > 0 {
				counter[Y]--
				counter[YZ]++
			} else {
				if counter[XY] > 0 {
					counter[XY]--
					counter[YZ]++
					counter[X]++
				} else {
					return false
				}
			}
		}
	}
	if counter[X] == 0 && counter[Y] == 0 && counter[Z] == 0 ||
		counter[X] == 0 && counter[Y] == 0 && counter[XY] == counter[Z]/2 ||
		counter[X] == 0 && counter[Z] == counter[XY] && counter[Y] == counter[XY] {
		return true
	}
	return false
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		var count int
		fmt.Fscanln(in, &count)

		var line string
		fmt.Fscanln(in, &line)
		if CheckPair(line) {
			fmt.Fprintln(out, "YES")
		} else {
			fmt.Fprintln(out, "NO")
		}
	}
}
