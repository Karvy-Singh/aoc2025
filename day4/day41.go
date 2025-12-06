package main

import (
	"bufio"
	"fmt"
	"os"
)

func checkRoll(grid [][]string, x, y int) int {
	if x < 0 || y < 0 || x > len(grid)-1 || y > len(grid[0])-1 {
		return 0
	}
	if grid[x][y] == "@" || grid[x][y] == "x" {
		return 1
	}
	return 0
}

func findtotal(grid [][]string, x, y, total int) int {
	a := checkRoll(grid, x, y+1)
	b := checkRoll(grid, x+1, y)
	c := checkRoll(grid, x-1, y)
	d := checkRoll(grid, x, y-1)
	e := checkRoll(grid, x+1, y+1)
	f := checkRoll(grid, x-1, y-1)
	g := checkRoll(grid, x-1, y+1)
	h := checkRoll(grid, x+1, y-1)

	neighbours := a + b + c + d + e + f + g + h

	fmt.Printf("sum:%d %s %d %d", neighbours, grid[x][y], x, y)
	fmt.Println()

	if neighbours < 4 && grid[x][y] == "@" {
		grid[x][y] = "x"
		total += 1
		fmt.Printf("%d, %d", x, y)
		fmt.Println()
	}

	if x == len(grid)-1 && y == len(grid[0])-1 {
		return total
	}

	if x < len(grid)-1 && y == len(grid[0])-1 {
		return findtotal(grid, x+1, 0, total)
	}

	if x <= len(grid)-1 && y < len(grid[0])-1 {
		return findtotal(grid, x, y+1, total)
	}

	return total
}

func main() {
	file, err := os.Open("inputfile.txt")
	if err != nil {
		fmt.Println("file not found")
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	grid := make([][]string, 0)

	for scanner.Scan() {
		line := scanner.Text()
		row := make([]string, 0)
		for i := 0; i < len(line); i++ {
			row = append(row, string(line[i]))
		}
		grid = append(grid, row)
	}

	// 	for i := 0; i < len(grid); i++ {
	// 		for j := 0; j < len(grid[i]); j++ {
	// 			fmt.Println(grid[i][j])
	// 		}
	// 	}
	// fmt.Println()
	fmt.Println(findtotal(grid, 0, 0, 0))
}
