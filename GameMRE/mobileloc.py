import requests
from geopy.geocoders import Nominatim

def get_ip():
    try:
        url = 'http://ipinfo.io/json'
        response = requests.get(url)
        data = response.json()
        ip = data['ip']
        return ip
    except Exception as e:
        print(f"Error getting ip address: {e}")
        return None
    
def get_location(ip):
    try:
        url = f'http://ipinfo.io/{ip}/json'
        response = requests.get(url)
        data = response.json()
        return data['loc']
    except Exception as e:
        print(f"Error getting ip address: {e}")
        return None
    
def get_address(latitute, longitude):
    try:
        geolocator = Nominatim(user_agent="geoapiExercises")
        location = geolocator.reverse(f"{latitute}, {longitude}")
        return location.address
    except Exception as e:
        print(f"Error getting ip address: {e}")
        return None
    
def main():
    ip = get_ip()
    if ip:
        print(f"IP: {ip}")
        location = get_location(ip)
        print(f"Location: {location}")
        if location:
            lat, lon = location.split(',')
            address = get_address(lat, lon)
            print(f"Address: {address}")
    
if __name__ == "__main__" :
    main()