export SETUPTOOLS_USE_DISTUTILS=stdlib
sudo apt-get update -y && sudo apt-get install -y build-essential make libenchant-dev enchant git dialog apt-utils && sudo apt-get autoremove && sudo apt-get clean
python3 -m pip install --upgrade setuptools
