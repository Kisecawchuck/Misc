import requests

def get_usd_to_brl():
    url = "https://cdn.jsdelivr.net/npm/@fawazahmed0/currency-api@latest/v1/currencies/usd.json"

    try:
        response = requests.get(url)
        response.raise_for_status()

        data = response.json()
        brl = str(data["usd"]["brl"])
        with open('exchange.txt', 'w') as file:
            file.write(brl)

    except requests.RequestException as e:
        print("Error fetching conversion: ", e)

get_usd_to_brl()
