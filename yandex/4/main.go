package main

import (
	"errors"
	"log"
	"sync"
	"time"
)

type Job func() error

func RunAll(jobs []Job) error {
	if len(jobs) == 0 {
		return nil
	}
	ch := make(chan error)
	go func() {
		defer close(ch)
		wg := sync.WaitGroup{}
		for _, job := range jobs {
			if job == nil {
				continue
			}
			wg.Add(1)
			go func() {
				defer wg.Done()
				ch <- job()
			}()
		}
		wg.Wait()
	}()
	var firstErr error
	for err := range ch {
		if err != nil && firstErr == nil {
			firstErr = err
		}
	}
	return firstErr
}

func main() {
	errFast := errors.New("fast")
	errSlow := errors.New("slow")

	jobs := []Job{
		func() error { time.Sleep(30 * time.Millisecond); return errFast },
		func() error { time.Sleep(80 * time.Millisecond); return errSlow },
		func() error { time.Sleep(100 * time.Millisecond); return nil },
	}

	err := RunAll(jobs)
	if err != nil {
		log.Println(err)
	} else {
		log.Println("all jobs completed successfully")
	}
}
