# 接口文档

## 实体 

### User（用户表）

#### 结构

* SQL 语句

```sql
# MYSQL
CREATE TABLE `manageuser` (
  `userID` int NOT NULL,
  `account` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `level` int DEFAULT NULL,
  `phoneNumber` varchar(14) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `userName` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`userID`) USING BTREE,
  UNIQUE KEY `account` (`account`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci ROW_FORMAT=DYNAMIC;
```

* Example

```json
{
  "userId": 5,
  "account": "user123",
  "userName": "John Doe",
  "password": "password123",
  "phoneNumber": "123456789",
  "level": 1
}
```

#### 增删改查

