package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	//runtime.GOMAXPROCS(1)
	x := make(map[int]int, 1)
	m := sync.Mutex{}
	go func() {
		m.Lock()
		x[1] = 2
		m.Unlock()
	}()
	go func() {
		m.Lock()
		x[1] = 7
		m.Unlock()
	}()
	go func() {
		m.Lock()
		x[1] = 10
		m.Unlock()
	}()
	time.Sleep(100 * time.Millisecond)
	fmt.Println("x[1] =", x[1])
}
