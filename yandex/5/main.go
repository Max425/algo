package main

import "fmt"

type Pred[T any] func(T) bool

func Filter[T any](in <-chan T, pred Pred[T]) <-chan T {
	out := make(chan T)
	go func() {
		defer close(out)
		for t := range in {
			if pred(t) {
				out <- t
			}
		}
	}()
	return out
}

func main() {
	ch := make(chan int, 5)
	for i := 1; i <= 5; i++ {
		ch <- i
	}
	close(ch)

	filtered := Filter(ch, func(x int) bool { return x%2 == 0 })

	for val := range filtered {
		fmt.Println(val) // вывод: 2, 4
	}

}
