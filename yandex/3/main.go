package main

import (
	"fmt"
	"sync"
)

//Описание:
//Примените функцию fn к каждому элементу in параллельно с пулом из workers горутин. Результаты должны быть в том же порядке, что и во входном слайсе.
//Вход:
//• in — входные данные
//• fn — функция обработки
//• workers — количество рабочих горутин (≥1)
//Выход:
//Срез результатов длины len (in).
//Пример:
//• in= [1,2,31, fn(x)=x*x, workers=2 → [1,4,9]

// Сигнатура:
type MapFunc[T any, R any] func(T) R

func ParallelMap[T any, R any](in []T, fn MapFunc[T, R], workers int) []R {
	res := make([]R, len(in))
	ch := make(chan int)
	go func() {
		defer close(ch)
		for i := 0; i < len(in); i++ {
			ch <- i
		}
	}()
	wg := sync.WaitGroup{}
	for j := 0; j < workers; j++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for i := range ch {
				res[i] = fn(in[i])
			}
		}()
	}
	wg.Wait()

	return res
}

func main() {
	in := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	fn := func(x int) int { return x * x }
	workers := 4
	res := ParallelMap(in, fn, workers)
	fmt.Println(res)
}
