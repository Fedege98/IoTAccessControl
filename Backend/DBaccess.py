import datetime

import pyodbc



class DBaccess:

    def __init__(self, server, database, username, password):
        self.connection = pyodbc.connect(
            f'DRIVER={{ODBC Driver 17 for SQL Server}};'
            f'SERVER={server};'
            f'DATABASE={database};'
            f'UID={username};'
            f'PWD={password};'
        )

    def check_login(self, username, password):
        query = "SELECT * FROM [dbo].[Users] WHERE [name] = ? AND [password] = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(query, (username, password))
            result = cursor.fetchall()

        return len(result) == 1

    def user_has_access_to_building(self, user_id, device_id):
        building_id_query = """SELECT [Id_Building] FROM [dbo].[Device] WHERE [id] = ?"""
        with self.connection.cursor() as cursor:
            cursor.execute(building_id_query, device_id)
            building_id = cursor.fetchone()[0]

        access_query = """SELECT COUNT(*) FROM [dbo].[UsersBuildings] WHERE [UserId] = ? AND [BuildingId] = ?"""
        with self.connection.cursor() as cursor:
            cursor.execute(access_query, (user_id, building_id))
            count = cursor.fetchone()[0]

        return count > 0

    def register_entry_log(self, user_id, device_id, access_code):
        access_time = datetime.datetime.now()
        building_id_query = "SELECT Id_Building FROM Device WHERE id = <device_id>"
        excecute_query = self.connection.execute(building_id_query)
        # Crea la query SQL per inserire il nuovo log
        query = f'INSERT INTO EntryLogs (user_id,{excecute_query}, access_time, access_code) VALUES (?, ?, ?, ?)'

        # Esegue la query utilizzando i parametri forniti
        with self.connection.cursor() as cursor:
            cursor.execute(query, user_id, device_id, access_time, access_code)
            self.connection.commit()

    def close(self):
        self.connection.close()
