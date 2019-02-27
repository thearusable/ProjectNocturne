pipeline {
  agent any
  stages {
    stage('Clone') {
      steps {
        git(url: 'https://github.com/thearusable/ProjectNocturne', branch: 'master', changelog: true)
      }
    }
    stage('Build') {
      steps {
        build 'build nocturne'
      }
    }
  }
}