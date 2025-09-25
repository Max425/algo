package main

import (
	"context"
	"net/http"
	"time"
)

// структура результата
type StatusResult struct {
	URL  string
	Code int
	Err  error
}

func FetchStatuses(
	urls []string,
	concurrency int,
	timeout time.Duration,
) []StatusResult {
	results := make([]StatusResult, len(urls))
	sem := make(chan struct{}, concurrency) // семафор для ограничения одновременных запросов
	done := make(chan struct{})

	for i, url := range urls {
		i, url := i, url
		sem <- struct{}{} // занять слот
		go func() {
			defer func() { <-sem }() // освободить слот
			ctx, cancel := context.WithTimeout(context.Background(), timeout)
			defer cancel()

			req, err := http.NewRequestWithContext(ctx, http.MethodGet, url, nil)
			if err != nil {
				results[i] = StatusResult{URL: url, Code: 0, Err: err}
				return
			}

			resp, err := http.DefaultClient.Do(req)
			if err != nil {
				results[i] = StatusResult{URL: url, Code: 0, Err: err}
				return
			}
			defer resp.Body.Close()

			results[i] = StatusResult{URL: url, Code: resp.StatusCode, Err: nil}
		}()
	}

	// дождаться всех горутин: занять все слоты
	for j := 0; j < cap(sem); j++ {
		sem <- struct{}{}
	}
	close(done)

	return results
}
