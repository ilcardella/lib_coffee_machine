ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

ENV_VARS = UID=$(shell id -u) GID=$(shell id -g)
DOCKER_COMPOSE = $(ENV_VARS) docker-compose -f docker/docker-compose.yml up --build
DOCKER_BUILD = $(ENV_VARS) docker-compose -f docker/docker-compose.yml build --force-rm
DOCKER_RUN = $(ENV_VARS) docker-compose -f docker/docker-compose.yml run --rm

default: ci

build-docker:
> $(DOCKER_BUILD) lib_coffee_machine_builder

test: build-docker
> $(DOCKER_RUN) lib_coffee_machine_builder scripts/test-project.sh

docs:
> $(DOCKER_COMPOSE) --exit-code-from docs-builder docs-builder

ci: test docs

clean:
> rm -rf build

.PHONY: default docs ci test build-docker clean