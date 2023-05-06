import random
from flask import Flask, request, jsonify
from Backend.DBaccess import DBaccess
from flask_swagger import swagger
from flask_swagger_ui import get_swaggerui_blueprint
from flask_restful import Api, Resource

app = Flask(__name__)
api = Api(app)
swagger = swagger(app)
SWAGGER_URL = '/api/docs'
API_URL = '/static/swagger.json'

swaggerui_blueprint = get_swaggerui_blueprint(
    SWAGGER_URL,
    API_URL,
    config={
        'app_name': "IoT Access Control API"
    }
)

app.register_blueprint(swaggerui_blueprint, url_prefix=SWAGGER_URL)

# Variabile globale per memorizzare il codice corrente
current_code = None
id_device = None


@app.route('/iotmessage', methods=['POST'])
def iot_message():
    global current_code
    try:
        data = request.get_json(force=True)

        id_device = data.get('id_device')
        code = data.get('code')

        if id_device is None or code is None:
            return jsonify({"error": "Invalid payload"}), 400

        # Fai qualcosa con id_device e code, ad esempio:
        print(f"Received message from device {id_device} with code {code}")

        # Memorizza il codice corrente nella variabile globale
        current_code = code

        return jsonify({"success": True}), 200
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@app.route('/firstcode', methods=['GET'])
def first_code():
    global current_code
    if current_code is None:
        return jsonify({"error": "No code received yet"}), 404

    return jsonify({"code": current_code, "id_device": id_device}), 200


@app.route('/login', methods=['POST'])
def logincheck():
    try:
        data = request.get_json(force=True)
        username = data.get('name')
        password = data.get('password')

        if username is None or password is None:
            return jsonify({"error": "Invalid username and password, insert again"}), 400

        if DBaccess.check_login(username, password):
            return jsonify({"success": True, "message": "Login successful"}), 200
        else:
            return jsonify({"error": "Incorrect username or password"}), 401
    except Exception as e:
        return jsonify({"error": str(e)}), 500


@app.route('/firstcodechecker', methods=['POST'])
def first_code_checker():
    try:
        data = request.get_json(force=True)
        user_id = data.get('user_id')
        code = data.get('code')

        if user_id is None or code is None:
            return jsonify({"error": "Invalid payload"}), 400

        if code != current_code:
            return jsonify({"error": "Incorrect code"}), 401

        if DBaccess.user_has_access_to_building(user_id, id_device):
            DBaccess.register_entry_log(user_id=user_id, device_id=id_device, access_code=access_code)
            return jsonify({"success": True, "message": "User has access to the building"}), 200

        else:
            return jsonify({"error": "User does not have access to the building"}), 403
    except Exception as e:
        return jsonify({"error": str(e)}), 500


# Funzione per generare un nuovo codice casuale
def generate_new_code():
    return random.randint(1000, 9999)


@app.route('/accesscode', methods=['POST'])
def access_code():
    try:
        data = request.get_json(force=True)
        user_id = data.get('user_id')
        building_id = data.get('building_id')
        first_code = data.get('code')

        if user_id is None or building_id is None or first_code is None:
            return jsonify({"error": "Invalid payload"}), 400

        # Verifica il first code e l'accesso al building
        data_check = {
            "user_id": user_id,
            "building_id": building_id,
            "code": first_code
        }
        check_response = first_code_checker(data_check)

        # Se il controllo ha avuto successo, genera e invia il nuovo codice
        if check_response.status_code == 200:
            new_code = generate_new_code()
            return jsonify({"success": True, "access_code": new_code}), 200
        else:
            return jsonify({"error": "Failed to verify first code or user access to the building"}), 403

    except Exception as e:
        return jsonify({"error": str(e)}), 500


@app.route('/static/<path:path>')
def send_static(path):
    return send_from_directory('static', path)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080, debug=True)
