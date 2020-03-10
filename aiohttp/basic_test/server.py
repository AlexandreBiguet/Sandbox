from aiohttp import web
import json

# https://docs.aiohttp.org/en/stable/


async def handle_get_name(request):
    name = request.match_info.get('name', "Anonymous")
    text = "Hello, " + name
    return web.Response(text=text)


async def handle_value(request):
    json_input = await request.json()
    print(json_input)
    data = {'some': 'data'}
    return web.json_response(data)


app = web.Application()
app.add_routes([web.get('/', handle_get_name),
                web.get('/{name}', handle_get_name),
                web.post('/value', handle_value)]
               )

if __name__ == '__main__':
    web.run_app(host='127.0.0.1', port=8080, app=app)
