package main

import (
	"net/http"
	_ "net/http/pprof"
	"os"
	"runtime/pprof"
	"time"
)
import "C"

//export go_start_cpuprofile
func go_start_cpuprofile() {
	file := "/tmp/test_cpu.prof"
	f, _ := os.Create(file)
	pprof.StartCPUProfile(f)
}

//export go_stop_cpuprofile
func go_stop_cpuprofile() {
	pprof.StopCPUProfile()
}

//export go_memprofile
func go_memprofile() {
	file := "/tmp/test_mem.prof"
	f, _ := os.Create(file)
	pprof.WriteHeapProfile(f)
	f.Close()
}

//export go_listenAndServe
func go_listenAndServe() {
	go func() {
		http.ListenAndServe("localhost:6060", nil)
	}()
}

//export go_leakyFunc
func go_leakyFunc() {
	s := make([]string, 3)
	for i := 0; i < 1000000; i++ {
		s = append(s, "magical pandas")
		if (i % 100000) == 0 {
			time.Sleep(500 * time.Millisecond)
		}
	}
}

func main() {}
