import requests

url = 'http://127.0.0.1:8000/upload'
file_path = 'test.txt'

with open(file_path, 'rb') as f:
    files = {'file': (file_path, f)}  # 'file' — имя поля для файла
    response = requests.post(url, files=files)

print(response.status_code, response.text)