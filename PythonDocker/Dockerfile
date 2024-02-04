# Use the official Python image as the base image
FROM python:3.8

# Set the working directory in the container
WORKDIR /app

# Copy the hello.py file from your local directory into the container at /app
COPY hello.py .

# Run the Python program when the container starts
CMD ["python", "hello.py"]