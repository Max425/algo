package main

import (
	"fmt"
	"sync"
)

func Tee[T any](in <-chan T) (<-chan T, <-chan T) {
	out1 := make(chan T)
	out2 := make(chan T)

	go func() {
		defer close(out1)
		defer close(out2)

		for v := range in {
			var wg sync.WaitGroup
			wg.Add(2)

			// запись в out1
			go func(val T) {
				defer wg.Done()
				out1 <- val
			}(v)

			// запись в out2
			go func(val T) {
				defer wg.Done()
				out2 <- val
			}(v)

			// ждём, пока оба значения будут отправлены
			wg.Wait()
		}
	}()

	return out1, out2
}

func main() {
	ch := make(chan int, 2)
	ch <- 10
	ch <- 20
	close(ch)

	out1, out2 := Tee(ch)

	go func() {
		for val := range out1 {
			fmt.Println("out1:", val)
		}
	}()

	for val := range out2 {
		fmt.Println("out2:", val)
	}
	// вывод:
	// out1: 10
	// out2: 10
	// out1: 20
	// out2: 20

}
