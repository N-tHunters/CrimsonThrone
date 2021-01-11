#!/bin/python3

import pygame

screen = pygame.display.set_mode((400, 400))

done = False

player_pos = [100, 100]
player_v = [0, 0]
player_width = 20

box_pos = [200, 200]
box_width = 40

while not done:
	player_pos[0] += player_v[0]

	if player_pos[0] + player_width / 2 >= box_pos[0] - box_width / 2:
		if player_pos[0] - player_width / 2 <= box_pos[0] + box_width / 2:
			if player_pos[1] + player_width / 2 >= box_pos[1] - box_width / 2:
				if player_pos[1] - player_width / 2 <= box_pos[1] + box_width / 2:
					player_pos[0] -= player_v[0]

	player_pos[1] += player_v[1]

	if player_pos[0] + player_width / 2 > box_pos[0] - box_width / 2:
		if player_pos[0] - player_width / 2 < box_pos[0] + box_width / 2:
			if player_pos[1] + player_width / 2 > box_pos[1] - box_width / 2:
				if player_pos[1] - player_width / 2 < box_pos[1] + box_width / 2:
					player_pos[1] -= player_v[1]

	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			done = True
		if e.type == pygame.KEYDOWN:
			if e.key == pygame.K_w:
				player_v[1] = -0.1
			if e.key == pygame.K_a:
				player_v[0] = -0.1
			if e.key == pygame.K_s:
				player_v[1] = 0.1
			if e.key == pygame.K_d:
				player_v[0] = 0.1
			elif e.key == pygame.K_q:
				done = True
		if e.type == pygame.KEYUP:
			if e.key == pygame.K_w and player_v[1] < 0:
				player_v[1] = 0
			if e.key == pygame.K_a and player_v[0] < 0:
				player_v[0] = 0
			if e.key == pygame.K_s and player_v[1] > 0:
				player_v[1] = 0
			if e.key == pygame.K_d and player_v[0] > 0:
				player_v[0] = 0
			elif e.key == pygame.K_q:
				done = True

	screen.fill((0, 0, 0))

	x = int(player_pos[0] - player_width // 2)
	y = int(player_pos[1] - player_width // 2)

	pygame.draw.rect(screen, (255, 255, 255), (x, y, player_width, player_width))

	x = int(box_pos[0] - box_width // 2)
	y = int(box_pos[1] - box_width // 2)

	pygame.draw.rect(screen, (255, 150, 0), (x, y, box_width, box_width))

	pygame.display.update()
pygame.quit()