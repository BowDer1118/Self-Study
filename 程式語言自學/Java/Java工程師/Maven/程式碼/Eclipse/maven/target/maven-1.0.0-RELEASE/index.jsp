<%@ page language="java" contentType="text/html; charset=BIG5"
    pageEncoding="BIG5"%>
<!-- 調用jstl -->
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="BIG5">
<title>Maven Test</title>
</head>
<body>
	This is maven project!!
	<fmt:formatNumber value="123456789.54321" pattern="0,000.00"></fmt:formatNumber>
</body>
</html>