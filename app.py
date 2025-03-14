from flask import Flask, render_template, request, jsonify, redirect, url_for, g
import os

print("Current working directory:", os.getcwd())  # Вывод текущей рабочей директории

app = Flask(__name__, template_folder='templates')  # Явно указываем папку с шаблонами

 #Создаем директорию uploads при старте сервера
if not os.path.exists('uploads'):
    os.makedirs('uploads')

@app.route('/upload', methods=['POST'])
def upload():
    if 'file' not in request.files:
        return 'No file part', 400

    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400

    # Сохраняем файл
    file_path = os.path.join('uploads', file.filename)
    file.save(file_path)
    return f'File saved to {file_path}', 200

if __name__ == "__main__":
    app.run(port=8000)