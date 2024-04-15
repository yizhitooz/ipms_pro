import sqlite3
from datetime import datetime, timedelta

# 连接到SQLite数据库
conn = sqlite3.connect('ipms.db')
cursor = conn.cursor()

def insert_data_when_enter(timestamp_enter,license_plate, plate_type, car_color):
    # 查询过去十分钟内的记录
    query_0 = """
    SELECT * FROM vehicle_records
    WHERE license_plate = ?
    AND timestamp_enter > ?
    """
    # 计算十分钟前的时间
    ten_minutes_ago = datetime.now() - timedelta(minutes=10)
    # 执行查询
    cursor.execute(query_0, (license_plate, ten_minutes_ago.strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]))

    # 如果没有找到记录，则插入新记录
    if cursor.fetchone() is None:
        query_1 = """
        INSERT INTO vehicle_records (timestamp_enter, license_plate, plate_type, car_color)
        VALUES (?, ?, ?, ?)
        """
        # 使用提供的数据执行插入
        cursor.execute(query_1, (timestamp_enter, license_plate, plate_type, car_color))
        # 提交更改到数据库
        conn.commit()
