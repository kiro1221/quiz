# quiz
docker build --platform linux/amd64 -t seleep-app .
docker run --platform linux/amd64 -p 9100:9100 --name seleep-container seleep-app