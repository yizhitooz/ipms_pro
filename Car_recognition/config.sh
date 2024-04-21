python -V # 检查Python是否安装好
python -m venv venv # 创建虚拟环境
venv\Scripts\activate # 进入虚拟环境
pip install -r requirements.txt # 安装需要的软件包
pip3 install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121 # 安装torch
