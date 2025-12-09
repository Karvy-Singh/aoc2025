package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	file, err := os.Open("inputfile.txt")
	if err != nil {
		fmt.Println("file not found")
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		values := make([]string, 0)
		for _, word := range strings.Fields(line) {
			values = append(values, word)
		}
		nums := make([]string, 0)
		ops := make([]string, 0)
		col := 0
		for _, i := range values {
			if i == "*" || i == "+" {
				col += 1
				ops = append(ops, i)
			} else {
				nums = append(nums, i)
			}
		}

		// pointer := 0
		total := 0
		for i, op := range ops {
			localsum := 0
			localmul := 1

			if op == "*" {
				for j := i; j < len(nums); j += col {
					num, err := strconv.Atoi(nums[j])
					// fmt.Printf("%d ", num)
					if err != nil {
						continue
					}
					// fmt.Println()
					localmul *= num
				}
				total += localmul
			} else if op == "+" {
				for j := i; j < len(nums); j += col {
					num, err := strconv.Atoi(nums[j])
					// fmt.Printf("%d ", num)
					localsum += num
					if err != nil {
						continue
					}
					// fmt.Println()
				}
				total += localsum
			}

		}
		fmt.Println(total)
	}
}
