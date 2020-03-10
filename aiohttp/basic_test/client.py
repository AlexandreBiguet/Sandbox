import aiohttp
import asyncio


async def fetch(session, url):
    async with session.get(url) as response:
        return await response.text()


async def post(session, url, body):
    async with session.post(url, json=body) as response:
        try:
            return await response.json()
        except Exception as err:
            print('error: ', err)


async def main():
    async with aiohttp.ClientSession() as session:
        html = await fetch(session, 'http://127.0.0.1:8080/coucou')
        print(html)

    async with aiohttp.ClientSession() as session:
        print(await post(session, url='http://127.0.0.1:8080/value',
                         body={'coucou': '1'}))


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
