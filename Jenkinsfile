pipeline {
  agent {
    node {
      label 'nocturne'
    }

  }
  stages {
    stage('checkout') {
      steps {
        git(url: 'https://github.com/thearusable/ProjectNocturne', branch: 'develop', changelog: true)
      }
    }
  }
}