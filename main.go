package main

import "fmt"

func powNums(nums []int) []int {
	res := make([]int, len(nums))
	left, right := 0, len(nums)-1
	for left <= right {
		if nums[left]*nums[left] > nums[right]*nums[right] {
			res[right-left] = nums[left] * nums[left]
			left++
		} else {
			res[right-left] = nums[right] * nums[right]
			right--
		}
	}
	return res
}

func main() {
	nums := []int{-124, -23, -11, 0, 12, 12, 13, 35, 234}
	fmt.Println(powNums(nums))
}
