from setuptools import setup
import os
from glob import glob

package_name = 'diffbot_description'
setup(
    name=package_name,
    version='0.0.0',
    packages=[],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
         glob('launch/*.py')),
        (os.path.join('share', package_name, 'urdf'),
         glob('urdf/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='chaotic-legend',
    maintainer_email='chaotic-legend@todo.todo',
    description='Diffbot robot description package',
    license='TODO',
    tests_require=['pytest'],
)
