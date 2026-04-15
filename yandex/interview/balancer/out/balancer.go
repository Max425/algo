package out

import (
	"context"
	"math"
	"sync"
)

type Request interface{}

type Response interface{}

type Backend interface {
	Invoke(ctx context.Context, req Request) (Response, error)
}

var _ Backend = &BackendImpl{}

// addr содержит ip:port конкретного экземпляра
func NewBackend(addr string) *BackendImpl

type Balancer struct {
	backends []*BackendWorker
	counters []int
	mu       sync.RWMutex
}

type BackendWorker struct {
	backend *BackendImpl
}

var _ Backend = &Balancer{}

// addrs содержат адреса всех балансируемых экземпляров
func NewBalancer(addrs []string) *Balancer {
	b := &Balancer{
		backends: make([]*BackendWorker, 0, len(addrs)),
		counters: make([]int, len(addrs)),
	}
	for _, addr := range addrs {
		b.backends = append(b.backends, &BackendWorker{
			backend: NewBackend(addr),
		})
	}
	return b
}

func (b *Balancer) Invoke(ctx context.Context, req Request) (Response, error) {
	var minBackIndex int
	minCount := math.MaxInt64

	b.mu.Lock()
	for i := range b.backends {
		count := b.counters[i]
		if count < minCount {
			minCount = count
			minBackIndex = i
		}
	}
	b.counters[minBackIndex]++
	b.mu.Unlock()

	req, err := b.backends[minBackIndex].backend.Invoke(ctx, req)

	b.mu.Lock()
	b.counters[minBackIndex]--
	b.mu.Unlock()

	return req, err
}
