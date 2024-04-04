package main

// Задача "Асинхронное слияние каналов"
// Реализовать функцию asyncMerge, которая будет производить асинхронное слияние каналов.

import (
	"fmt"
	"sync"
)

// Исходные данные:
func main() {
	ch1 := make(chan int, 10)
	ch2 := make(chan int, 20)

	ch1 <- 1
	ch2 <- 2
	ch2 <- 4

	close(ch1)
	close(ch2)

	ch3 := asyncMerge[int](ch1, ch2)

	for val := range ch3 {
		fmt.Println(val)
	}
}

func asyncMerge[T any](chans ...chan T) chan T {
	ch := make(chan T)
	wg := &sync.WaitGroup{}

	for _, el := range chans {
		wg.Add(1)

		go func(el chan T) {
			for x := range el {
				ch <- x
			}
			wg.Done()
		}(el)
	}

	go func() {
		wg.Wait()
		close(ch)
	}()

	return ch
}
