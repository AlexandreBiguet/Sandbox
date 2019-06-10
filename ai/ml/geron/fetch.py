
import os
import tarfile
import urllib.request


def fetch_data(remote_path, local_path_prefix, local_path):

    path = local_path_prefix + '/' + local_path

    if not os.path.isdir(os.path.dirname(path)):
        os.makedirs(os.path.dirname(path))

    if not os.path.exists(path):
        urllib.request.urlretrieve(url=remote_path, filename=path)

    tgz = tarfile.open(path)
    tgz.extractall(path=os.path.dirname(path))
    tgz.close()
