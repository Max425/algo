package main

import "fmt"

func main() {
	var n int
	fmt.Scanf("%d\n", &n)
	for i := 0; i < n; i++ {
		var s string
		fmt.Scanf("%s\r\n", &s)
		res := []string{""}
		var pointer, stroka int
		for _, c := range s {
			switch string(c) {
			case "L":
				if pointer > 0 {
					pointer--
				}
			case "R":
				if pointer < len(res[stroka]) {
					pointer++
				}
			case "U":
				if stroka > 0 {
					stroka--
					if pointer > len(res[stroka]) {
						pointer = len(res[stroka])
					}
				}
			case "D":
				if stroka < len(res)-1 {
					stroka++
					if pointer > len(res[stroka]) {
						pointer = len(res[stroka])
					}
				}
			case "B":
				pointer = 0
			case "E":
				pointer = len(res[stroka])
			case "N":
				newString := res[stroka][pointer:]
				res[stroka] = res[stroka][:pointer]
				var newRes []string
				newRes = append(newRes, res[:stroka+1]...)
				newRes = append(newRes, newString)
				newRes = append(newRes, res[stroka+1:]...)
				res = newRes
				stroka++
				pointer = 0
			default:
				res[stroka] = res[stroka][:pointer] + string(c) + res[stroka][pointer:]
				pointer++
			}
		}

		for _, j := range res {
			fmt.Println(j)
		}
		fmt.Println("-")
	}
}
