api: greet.pb.go 

greet.pb.go: 
	# @protoc --go_out=$(shell pwd)/api --proto_path=$(shell pwd)/../api greet.proto
	@protoc --proto_path=./api greet.proto --go_out=plugins=grpc:./api

all: api

run: 
	@go run main.go