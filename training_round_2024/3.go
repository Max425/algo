package main

import (
	"fmt"
)

func isFigure(s uint8) bool {
	c := string(s)
	return "0" <= c && c <= "9"
}

func isLetter(s uint8) bool {
	c := string(s)
	return "A" <= c && c <= "Z"
}

func isCorrect(number string) bool {
	if len(number) == 4 {
		return isLetter(number[0]) && isFigure(number[1]) && isLetter(number[2]) && isLetter(number[3])
	} else if len(number) == 5 {
		return isLetter(number[0]) && isFigure(number[1]) && isFigure(number[2]) && isLetter(number[3]) && isLetter(number[4])
	}
	return false
}

func main() {
	var n int
	fmt.Scanf("%d\r\n", &n)

	for j := 0; j < n; j++ {
		var s, res string
		var flag bool
		fmt.Scanf("%s\r\n", &s)

		for i := 0; i < len(s); {
			flag = true
			if i+4 <= len(s) && isCorrect(s[i:i+4]) {
				res += s[i:i+4] + " "
				i += 4
			} else if i+5 <= len(s) && isCorrect(s[i:i+5]) {
				res += s[i:i+5] + " "
				i += 5
			} else {
				flag = false
				break
			}
		}

		if flag {
			fmt.Println(res)
		} else {
			fmt.Println("-")
		}
	}
}
