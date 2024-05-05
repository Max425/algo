package main

import (
	"bufio"
	"fmt"
	"os"
)

func isSimilar(s1, s2 string) bool {
	if s1 == s2 {
		return true
	}
	swap := false
	for i := 0; i < len(s1); i++ {
		if s1[i] == s2[i] {
			continue
		}
		if i < len(s1)-1 && !swap && s1[i] == s2[i+1] && s1[i+1] == s2[i] {
			i++
			swap = true
			continue
		}
		return false
	}
	return true
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	fmt.Fscanln(in, &n)

	logins := make(map[int][]string, n)
	for i := 0; i < n; i++ {
		var line string
		fmt.Fscanln(in, &line)
		logins[len(line)] = append(logins[len(line)], line)
	}

	var m int
	fmt.Fscanln(in, &m)

	newLogins := make([]string, m)
	for i := 0; i < m; i++ {
		fmt.Fscanln(in, &newLogins[i])
	}

	for _, t := range newLogins {
		found := false
		for _, s := range logins[len(t)] {
			if isSimilar(s, t) {
				found = true
				break
			}
		}
		if found {
			fmt.Println(1)
		} else {
			fmt.Println(0)
		}
	}
}
