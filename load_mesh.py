# Import pour visualiser dans Blender
# Roucheyrolles Benjamin
# Licence Pro SIL Image et Son 2006/2007 

import Blender
from Blender import NMesh

objmesh='terrain'
rawfile=open("filepath:\\Fractal\\fractal.raw","r")
tabraw=rawfile.readlines()
rawfile.close()

mesh=NMesh.GetRaw()

for ligne in tabraw:

	ligne=ligne.replace('\n','')
	l=ligne.split(' ')
	
	# Création des coordonnées
	x=float(l[0])
	y=float(l[1])
	z=float(l[2])
	
	v=NMesh.Vert(x,y,z)
	mesh.verts.append(v)

NMesh.PutRaw(mesh,objmesh)

for i in range(0,n-1,1):
	for j in range(0,n-1,1):
		f = NMesh.Face()
		f.v.append(mesh.verts[i*n+j])
		f.v.append(mesh.verts[i*n+j+1])
		f.v.append(mesh.verts[(i+1)*n+j+1])
		f.v.append(mesh.verts[(i+1)*n+j])
		f.smooth=1
		mesh.faces.append(f)

NMesh.PutRaw(mesh,objmesh) 