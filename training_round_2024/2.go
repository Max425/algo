package main

import "fmt"

func isLeapYear(year int) bool {
	return (year%4 == 0 && year%100 != 0) || (year%400 == 0)
}

func isValidDate(day, month, year int) bool {
	if day < 1 || day > 31 {
		return false
	}

	if month < 1 || month > 12 {
		return false
	}

	if year < 1950 || year > 2300 {
		return false
	}

	daysInMonth := [13]int{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	if isLeapYear(year) {
		daysInMonth[2] = 29
	}

	return day <= daysInMonth[month]
}

func main() {
	var n int
	fmt.Scanf("%d\n", &n)

	var day, month, year int
	for i := 0; i < n; i++ {
		fmt.Scanf("%d %d %d\n", &day, &month, &year)

		if isValidDate(day, month, year) {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}
}
