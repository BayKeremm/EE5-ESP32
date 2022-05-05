import requests
url = 'https://a21iot15.studev.groept.be/index.php/api/'
token = '?token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InRlc3QiLCJleHAiOjE2NTY3NjkxNjd9.P_ZNXq5XKOVP9ZBGH8HyI5TNrMqcH7a9k08yJMzwpTY'
def registerUser(userName,password):
    urlRegister = url+'register'+'/'+userName+'/'+password
    result = requests.post(urlRegister)
    return result
def loginUser(userName,password):
    urlLogin = url+'login'+'/'+userName+'/'+password
    result = requests.post(urlLogin)
    return result
def getDeviceId(ownershipId):
    urlDevId = url+'getDeviceId'+'/'+ownershipId+token
    result = requests.get(urlDevId)
    return result
def getIdealParameters(deviceId):
    urlIdeal = url+'getIdealParams'+'/'+deviceId+token
    result = requests.get(urlIdeal)
    return result
def dayParameters():
    urlDay = url+'day'+token
    result = requests.get(urlDay)
    return result
def updateOwnedPlant(userId,plantId,imgBinary,nickName):
    urlUpdt = url+'updateOwnedPlant'+'/'+userId+'/'+plantId+'/'+imgBinary+'/'+nickName+token
    result = requests.post(urlUpdt )
    return result
def insertOwnedPlant(userId,plantId,deviceId,nickName):
    urlInst = url+'insertOwnedPlant'+'/'+userId+'/'+plantId+'/'+deviceId+'/'+nickName+token
    result = requests.post(urlInst)
    return result
def listOwnedPlants(userId):
    urlList = url+'listOwnedPlants'+'/'+userId+token
    result = requests.get(urlList)
    return result
def listPlants():
    urlListP = url+'listPlants'+token
    result = requests.get(urlListP)
    return result
def listMeasurements(limit,plantId):
    urlListM = url+'listMeasurements'+'/'+limit+'/'+plantId+token
    result = requests.get(urlListM)
    return result
def listUsers():
    urlListU = url+'listUsers'+token
    result = requests.get(urlListU)
    return result
def putMeasurement(Mtype,value,ownershipId):
    urlPut = url+'put'+'/'+Mtype+'/'+value+'/'+ownershipId+token
    result = requests.post(urlPut)
    return result
if __name__ == '__main__':
    print("--Get deviceId test---")
    out = getDeviceId('34')
    print("output:")
    print(out.text)
  #  print("--user register test---")
  #  out = registerUser("DABABY","CONVERTIBLE")
  #  print("output:")
  #  print(out.text)

  #  print("--user login test---")
  #  out = loginUser("DABABY","CONVERTIBLE")
  #  print("output:")
  #  print(out.text)

  #  print("--Get ideal parameters test---")
  #  out = getIdealParameters('1')
  #  print("output:")
  #  print(out.text)

  #  print("--Get day parameter test---")
  #  out = dayParameters()
  #  print("output:")
  #  print(out.text)

  #  print("--update owned plant test---")
  #  out = updateOwnedPlant('9','1','111111',"Lesgoo")
  #  print("output:")
  #  print(out.text)

  #  print("--insert owned plant test---")
  #  out = insertOwnedPlant('10','2','1',"CONVERTIBLE")
  #  print("output:")
  #  print(out.text)

  #  print("--list owned plant test---")
  #  out = listOwnedPlants('9')
  #  print("output:")
  #  print(out.text)

  #  print("--list plants test---")
  #  out = listPlants()
  #  print("output:")
  #  print(out.text)

  #  print("--list measurements test---")
  #  out = listMeasurements('5','1')
  #  print("output:")
  #  print(out.text)

  #  print("--list users test---")
  #  out = listUsers()
  #  print("output:")
  #  print(out.text)

  #  print("--put measuerment test---")
  #  out = putMeasurement("Moisture",'69.96','42')
  #  print("output:")
  #  print(out.text)
