package main

import (
	"io/ioutil"
	"log"
	"net/http"
	"regexp"
	"time"
)

func do_nothing(str string) string {
	return str
}

func get_currency(str string) string {
	re := regexp.MustCompile("Currency is now (.*)")

	result := re.FindStringSubmatch(str)
	if len(result) > 1 {
		return result[1]
	} else {
		return str
	}
}

func site_parser(url string, port string, callback func(string) string) func(chan string) {
	return func(result chan string) {
		log.Println("Started " + url + ":" + port)
		resp, err := http.Get(url + ":" + port)
		if err != nil {
			log.Println("failed : ", err)
			result <- callback("<No result>")
			return
		}
		body, err := ioutil.ReadAll(resp.Body)
		log.Println("Done " + url + ":" + port)
		result <- callback(string(body[:]))
	}
}

func with_timeout(done chan bool, function func(chan string), timeout int) {
	var timeouted = make(chan bool)

	go func() {
		time.Sleep(time.Duration(timeout) * time.Second)
		timeouted <- true
	}()

	var result = make(chan string)
	go function(result)

	select {
	case <-timeouted:
		log.Println("Timeouted")
	case res := <-result:
		log.Println("result= ", res)
	}
	done <- true
}

func main() {
	var done = make(chan bool)

	go with_timeout(done, site_parser("http://127.0.0.1", "8001", get_currency), 3)
	go with_timeout(done, site_parser("http://127.0.0.1", "8000", get_currency), 3)

	for i := 0; i < 2; i++ {
		<-done
	}

}
