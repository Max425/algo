package main

import (
	"bufio"
	"fmt"
	"math"
	"math/big"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var testsCount int
	fmt.Fscanln(in, &testsCount)
	for i := 0; i < testsCount; i++ {
		var n, p float64
		fmt.Fscanln(in, &n, &p)

		var res float64
		for j := 0; j < int(n); j++ {
			var a float64
			fmt.Fscanln(in, &a)

			cost := big.NewFloat(a)
			pr := big.NewFloat(p / 100)
			kk := new(big.Float).Mul(cost, pr)
			data, _ := kk.Float64()

			k := math.Floor(data*100) / 100
			kErr := math.Floor(data)

			res += k - kErr
		}

		fmt.Fprintf(out, "%.2f\n", res)
	}
}
