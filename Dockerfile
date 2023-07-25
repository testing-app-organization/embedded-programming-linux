# Use a base image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Copy the necessary files to the container
COPY FlightService.cpp .
COPY myLibrary.h .
COPY myLibrary.cpp .
COPY full_schedule.h .
COPY full_schedule.cpp .
COPY arrivals.h .
COPY arrivals.cpp .
COPY airplane.h .
COPY airplane.cpp .
COPY signal_handler.h .
COPY signal_handler.cpp .
COPY error_handling.h .
COPY error_handling.cpp .
COPY zip.h .
COPY zip.cpp .
COPY pipe_handler.h .
COPY pipe_handler.cpp .
COPY node.h .

# Install required dependencies
RUN apt-get update && \
    apt-get install -y build-essential libzip-dev

# Build the application
RUN g++ -o myapp FlightService.cpp myLibrary.cpp full_schedule.cpp arrivals.cpp airplane.cpp signal_handler.cpp error_handling.cpp zip.cpp pipe_handler.cpp

# Set the entry point
ENTRYPOINT ["./myapp"]
