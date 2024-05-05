package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func CalcSeason(data []int) []int {
	result := make([]int, len(data)+1)
	var prevKSeason int
	lenKSeason := 1
	for i := 0; i < len(data); i++ {
		var up, down, kSeason int
		for i < len(data)-1 && data[i] < data[i+1] {
			up++
			i++
		}
		for i < len(data)-1 && data[i] > data[i+1] {
			down++
			i++
		}
		if up == 0 || down == 0 {
			if up > 0 || down > 0 {
				i--
			}
			prevKSeason, lenKSeason = 0, 1
			continue
		}
		if up <= down {
			kSeason = up
			if prevKSeason == kSeason {
				lenKSeason++
			} else {
				lenKSeason = 1
			}
			if lenKSeason > result[kSeason] {
				result[kSeason] = lenKSeason
				if kSeason > 1 {
					j := kSeason - 1
					for result[j] == 0 && j != 0 {
						result[j] = 1
						j--
					}
				}
			}
			if up == down {
				prevKSeason = kSeason
			} else {
				prevKSeason = 0
			}
		} else if up > down {
			kSeason = down
			prevKSeason, lenKSeason = kSeason, 1
			if lenKSeason > result[kSeason] {
				result[kSeason] = lenKSeason
				if kSeason > 1 {
					j := kSeason - 1
					for result[j] == 0 && j != 0 {
						result[j] = 1
						j--
					}
				}
			}
		}
		i--

	}

	return result
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testCount int
	fmt.Fscanln(in, &testCount)
	for i := 0; i < testCount; i++ {
		var n int
		fmt.Fscanln(in, &n)
		line, _ := in.ReadString('\n')

		data := make([]int, 0, n)
		for _, el := range strings.Split(strings.TrimSpace(line), " ") {
			num, _ := strconv.Atoi(el)
			data = append(data, num)
		}
		result := CalcSeason(data)
		for j := 1; j < len(result); j++ {
			if j == len(result)-1 {
				fmt.Fprintf(out, "%d", result[j])
			} else {
				fmt.Fprintf(out, "%d ", result[j])
			}
		}
		fmt.Fprintln(out)
	}
}
